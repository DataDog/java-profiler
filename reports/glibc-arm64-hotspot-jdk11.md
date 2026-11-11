---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 20:36:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794360772 43
1794360777 43
1794360782 43
1794360787 43
1794360792 43
1794360797 43
1794360802 43
1794360807 43
1794360812 43
1794360817 43
1794360822 43
1794360827 43
1794360832 43
1794360837 43
1794360842 43
1794360847 43
1794360852 43
1794360857 43
1794360862 43
1794360867 43
```
</details>

---

