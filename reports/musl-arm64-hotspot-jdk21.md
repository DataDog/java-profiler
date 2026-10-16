---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 10:46:18 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 9 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792161515 51
1792161520 51
1792161526 51
1792161531 51
1792161536 51
1792161541 51
1792161546 51
1792161551 51
1792161556 51
1792161561 51
1792161566 51
1792161571 51
1792161576 51
1792161581 51
1792161586 46
1792161591 46
1792161596 46
1792161601 46
1792161606 46
1792161611 46
```
</details>

---

