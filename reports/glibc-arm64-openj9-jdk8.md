---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-26 06:57:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793012007 46
1793012012 46
1793012017 46
1793012022 46
1793012027 46
1793012032 46
1793012037 46
1793012042 46
1793012047 51
1793012052 51
1793012057 51
1793012062 51
1793012067 51
1793012072 51
1793012077 51
1793012082 51
1793012087 51
1793012092 51
1793012098 51
1793012103 51
```
</details>

---

