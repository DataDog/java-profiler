---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:56:29 EDT

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
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 12 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1789677923 64
1789677928 64
1789677933 64
1789677938 64
1789677943 64
1789677948 64
1789677953 64
1789677958 64
1789677963 64
1789677968 30
1789677973 30
1789677978 30
1789677983 30
1789677988 30
1789677993 30
1789677998 30
1789678003 30
1789678008 30
1789678013 30
1789678018 30
```
</details>

---

