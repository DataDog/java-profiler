---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:40:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 40-44 cores)</summary>

```
1792787771 40
1792787776 40
1792787781 40
1792787786 40
1792787791 40
1792787796 40
1792787801 40
1792787806 40
1792787811 40
1792787816 40
1792787821 40
1792787826 40
1792787831 40
1792787836 40
1792787841 40
1792787846 40
1792787851 40
1792787856 40
1792787861 40
1792787866 40
```
</details>

---

