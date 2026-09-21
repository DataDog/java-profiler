---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:42:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 83-96 cores)</summary>

```
1789979860 83
1789979865 83
1789979870 96
1789979875 96
1789979880 96
1789979885 96
1789979890 96
1789979895 96
1789979900 96
1789979905 96
1789979910 96
1789979915 96
1789979920 96
1789979925 96
1789979930 96
1789979935 96
1789979940 96
1789979945 96
1789979950 96
1789979955 96
```
</details>

---

