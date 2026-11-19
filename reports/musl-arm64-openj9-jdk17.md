---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:38:13 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795109586 50
1795109591 50
1795109596 50
1795109601 50
1795109606 50
1795109611 50
1795109616 50
1795109621 50
1795109626 50
1795109631 50
1795109636 45
1795109641 45
1795109646 45
1795109651 45
1795109656 45
1795109661 45
1795109666 45
1795109671 45
1795109676 45
1795109681 45
```
</details>

---

