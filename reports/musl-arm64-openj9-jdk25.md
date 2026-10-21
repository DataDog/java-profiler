---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 16:06:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 10 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792612825 51
1792612830 51
1792612835 51
1792612840 51
1792612845 51
1792612850 51
1792612855 51
1792612860 51
1792612865 51
1792612870 51
1792612875 51
1792612880 51
1792612885 51
1792612890 51
1792612895 51
1792612900 51
1792612905 51
1792612910 51
1792612915 51
1792612920 46
```
</details>

---

