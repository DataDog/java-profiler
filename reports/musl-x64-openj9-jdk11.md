---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 06:21:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 9 |
| Allocations | 586 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794827797 32
1794827802 32
1794827807 32
1794827812 32
1794827817 32
1794827822 32
1794827827 32
1794827832 32
1794827837 32
1794827842 32
1794827847 32
1794827852 32
1794827857 32
1794827862 32
1794827867 32
1794827872 32
1794827877 32
1794827882 30
1794827887 30
1794827892 30
```
</details>

---

