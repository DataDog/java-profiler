---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 12:58:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795542772 64
1795542777 64
1795542782 64
1795542787 64
1795542792 64
1795542797 64
1795542802 64
1795542807 64
1795542812 64
1795542817 64
1795542822 64
1795542827 64
1795542832 64
1795542837 64
1795542842 64
1795542847 64
1795542852 64
1795542857 64
1795542862 64
1795542867 64
```
</details>

---

