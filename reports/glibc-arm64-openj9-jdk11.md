---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:06:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (6 unique values: 38-48 cores)</summary>

```
1786971607 38
1786971612 38
1786971617 38
1786971622 38
1786971627 38
1786971632 38
1786971637 38
1786971642 38
1786971647 43
1786971652 43
1786971657 42
1786971662 42
1786971667 42
1786971672 47
1786971677 47
1786971682 47
1786971687 47
1786971692 48
1786971697 48
1786971702 48
```
</details>

---

