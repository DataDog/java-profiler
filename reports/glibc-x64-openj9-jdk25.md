---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 16:27:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 10 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (5 unique values: 28-46 cores)</summary>

```
1794345836 28
1794345841 28
1794345846 28
1794345851 28
1794345856 45
1794345861 45
1794345866 45
1794345871 45
1794345876 43
1794345881 43
1794345886 43
1794345891 43
1794345896 43
1794345901 43
1794345906 46
1794345911 46
1794345916 37
1794345921 37
1794345926 37
1794345931 37
```
</details>

---

