---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-08 00:57:00 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (3 unique values: 14-24 cores)</summary>

```
1786164777 14
1786164782 14
1786164787 14
1786164792 14
1786164797 14
1786164802 14
1786164807 14
1786164812 14
1786164817 14
1786164822 19
1786164827 19
1786164832 19
1786164837 19
1786164842 19
1786164847 19
1786164852 19
1786164857 19
1786164862 19
1786164867 19
1786164872 19
```
</details>

---

