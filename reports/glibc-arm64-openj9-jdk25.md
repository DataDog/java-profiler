---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 09:45:19 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 12 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 14 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1791466787 44
1791466792 48
1791466797 48
1791466802 48
1791466807 43
1791466812 43
1791466817 43
1791466822 43
1791466827 43
1791466832 43
1791466837 43
1791466842 43
1791466847 43
1791466852 43
1791466857 48
1791466862 48
1791466867 48
1791466872 48
1791466877 48
1791466882 48
```
</details>

---

