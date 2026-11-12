---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:21:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 7 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 11-18 cores)</summary>

```
1794478522 13
1794478527 13
1794478532 13
1794478537 13
1794478542 13
1794478547 18
1794478552 18
1794478557 18
1794478562 18
1794478567 13
1794478572 13
1794478577 13
1794478582 13
1794478587 13
1794478592 11
1794478597 11
1794478602 11
1794478607 11
1794478612 11
1794478618 11
```
</details>

---

