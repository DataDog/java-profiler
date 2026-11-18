---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 05:43:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794998165 51
1794998170 51
1794998175 51
1794998180 51
1794998185 51
1794998190 51
1794998195 51
1794998201 51
1794998206 51
1794998211 51
1794998216 51
1794998221 51
1794998226 51
1794998231 51
1794998236 51
1794998241 51
1794998246 51
1794998251 46
1794998256 46
1794998261 46
```
</details>

---

