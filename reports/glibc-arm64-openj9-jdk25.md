---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:23:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 9 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 31-43 cores)</summary>

```
1790853592 31
1790853597 31
1790853602 31
1790853607 31
1790853612 31
1790853617 31
1790853622 31
1790853627 31
1790853632 31
1790853637 31
1790853642 43
1790853647 43
1790853652 43
1790853657 43
1790853662 43
1790853667 43
1790853672 43
1790853677 43
1790853682 43
1790853687 43
```
</details>

---

