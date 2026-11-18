---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:06:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 11 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1795010517 33
1795010522 33
1795010527 33
1795010532 33
1795010537 38
1795010542 38
1795010547 43
1795010552 43
1795010557 43
1795010562 43
1795010567 43
1795010572 43
1795010577 43
1795010582 43
1795010587 43
1795010592 43
1795010597 43
1795010602 43
1795010607 43
1795010612 43
```
</details>

---

