---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:22 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1795010502 51
1795010507 51
1795010512 51
1795010517 51
1795010522 51
1795010527 51
1795010532 51
1795010537 51
1795010542 51
1795010547 51
1795010552 51
1795010557 51
1795010562 51
1795010567 51
1795010572 51
1795010577 51
1795010582 51
1795010587 51
1795010592 51
1795010597 51
```
</details>

---

