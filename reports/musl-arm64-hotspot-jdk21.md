---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-02 13:35:51 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 196 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1788369938 48
1788369943 48
1788369948 48
1788369953 48
1788369958 48
1788369963 48
1788369968 48
1788369973 48
1788369978 48
1788369983 48
1788369988 48
1788369993 48
1788369998 48
1788370003 48
1788370008 48
1788370013 48
1788370018 48
1788370023 48
1788370028 48
1788370033 48
```
</details>

---

