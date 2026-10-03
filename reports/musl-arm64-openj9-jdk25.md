---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-03 04:34:58 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 42-59 cores)</summary>

```
1791016240 42
1791016245 42
1791016250 42
1791016255 42
1791016260 47
1791016265 47
1791016270 47
1791016275 47
1791016280 54
1791016285 54
1791016290 54
1791016295 54
1791016300 54
1791016305 54
1791016310 54
1791016315 54
1791016320 54
1791016325 54
1791016330 54
1791016335 54
```
</details>

---

