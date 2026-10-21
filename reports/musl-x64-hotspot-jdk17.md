---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:06:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1792612821 26
1792612826 26
1792612831 26
1792612836 28
1792612841 28
1792612846 28
1792612851 28
1792612856 28
1792612861 28
1792612866 28
1792612871 28
1792612876 28
1792612881 28
1792612886 28
1792612891 28
1792612896 28
1792612901 28
1792612906 28
1792612911 28
1792612916 30
```
</details>

---

