---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:27:33 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (2 unique values: 29-64 cores)</summary>

```
1795112641 29
1795112646 29
1795112651 29
1795112656 29
1795112661 29
1795112666 29
1795112671 29
1795112676 29
1795112681 29
1795112686 29
1795112691 29
1795112696 29
1795112701 29
1795112706 64
1795112711 64
1795112716 64
1795112721 64
1795112726 64
1795112731 64
1795112736 64
```
</details>

---

