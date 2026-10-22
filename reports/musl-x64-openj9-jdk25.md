---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 06:47:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792665757 32
1792665762 30
1792665767 30
1792665772 30
1792665777 30
1792665782 30
1792665787 30
1792665792 30
1792665797 32
1792665802 32
1792665807 32
1792665812 32
1792665817 32
1792665822 32
1792665827 32
1792665832 32
1792665837 32
1792665842 32
1792665847 32
1792665852 32
```
</details>

---

