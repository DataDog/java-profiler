---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 12:33:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1795022901 45
1795022906 45
1795022911 45
1795022916 45
1795022921 45
1795022926 45
1795022931 45
1795022936 45
1795022941 45
1795022946 45
1795022951 45
1795022956 47
1795022961 47
1795022966 47
1795022971 47
1795022976 45
1795022981 45
1795022986 45
1795022991 45
1795022996 45
```
</details>

---

