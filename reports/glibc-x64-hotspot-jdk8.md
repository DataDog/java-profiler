---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 12:33:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 29-50 cores)</summary>

```
1795022906 33
1795022911 33
1795022916 33
1795022921 33
1795022926 33
1795022931 33
1795022936 50
1795022941 50
1795022946 50
1795022951 50
1795022956 50
1795022961 50
1795022966 50
1795022971 50
1795022976 50
1795022981 50
1795022986 50
1795022991 50
1795022996 29
1795023001 29
```
</details>

---

