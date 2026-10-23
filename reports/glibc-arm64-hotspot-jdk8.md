---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-23 16:40:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1792787786 42
1792787791 42
1792787796 42
1792787801 42
1792787806 42
1792787811 40
1792787816 40
1792787821 40
1792787826 40
1792787831 40
1792787836 40
1792787841 40
1792787846 40
1792787851 42
1792787856 42
1792787861 48
1792787866 48
1792787871 48
1792787876 48
1792787881 48
```
</details>

---

