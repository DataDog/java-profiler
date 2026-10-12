---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 03:26:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791789744 48
1791789749 48
1791789754 48
1791789759 48
1791789764 48
1791789769 48
1791789774 48
1791789779 48
1791789784 48
1791789789 48
1791789794 48
1791789799 48
1791789804 48
1791789809 48
1791789815 48
1791789820 48
1791789825 48
1791789830 48
1791789835 48
1791789840 48
```
</details>

---

