---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-03 04:34:58 EDT

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
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791016230 48
1791016235 48
1791016240 38
1791016245 38
1791016250 38
1791016255 38
1791016260 38
1791016265 38
1791016270 38
1791016275 38
1791016280 38
1791016285 38
1791016290 38
1791016295 43
1791016300 43
1791016305 43
1791016310 43
1791016315 43
1791016320 43
1791016325 43
```
</details>

---

