---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:12:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1794931685 86
1794931690 86
1794931695 86
1794931700 86
1794931705 86
1794931710 86
1794931715 86
1794931720 88
1794931725 88
1794931730 88
1794931735 88
1794931740 88
1794931745 88
1794931750 88
1794931755 88
1794931760 88
1794931765 88
1794931770 88
1794931775 88
1794931780 88
```
</details>

---

