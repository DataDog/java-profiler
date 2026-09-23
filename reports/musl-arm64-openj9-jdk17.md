---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 11 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790168647 43
1790168652 48
1790168657 48
1790168662 43
1790168667 43
1790168672 38
1790168677 38
1790168682 38
1790168687 38
1790168692 38
1790168697 38
1790168702 38
1790168707 38
1790168712 38
1790168717 38
1790168722 38
1790168727 38
1790168732 38
1790168737 38
1790168742 43
```
</details>

---

