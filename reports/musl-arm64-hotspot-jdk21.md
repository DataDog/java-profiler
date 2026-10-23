---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 16:40:59 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 10 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792787776 39
1792787781 39
1792787786 39
1792787791 39
1792787796 51
1792787801 51
1792787806 51
1792787811 51
1792787816 51
1792787821 51
1792787826 51
1792787831 51
1792787836 51
1792787841 51
1792787846 51
1792787851 51
1792787856 51
1792787861 51
1792787866 51
1792787871 51
```
</details>

---

