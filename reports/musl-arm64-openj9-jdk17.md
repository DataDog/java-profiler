---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:51:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795632444 59
1795632449 59
1795632454 59
1795632459 59
1795632464 59
1795632469 59
1795632474 59
1795632479 59
1795632484 59
1795632489 59
1795632494 59
1795632499 59
1795632504 59
1795632509 59
1795632514 59
1795632519 59
1795632524 59
1795632529 64
1795632534 64
1795632539 64
```
</details>

---

