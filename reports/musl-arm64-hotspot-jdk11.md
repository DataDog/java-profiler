---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 20:19:43 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 10 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 969 |
| Sample Rate | 16.15/sec |
| Health Score | 1009% |
| Threads | 8 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 30-40 cores)</summary>

```
1787184898 30
1787184903 30
1787184908 30
1787184913 30
1787184918 32
1787184923 32
1787184928 32
1787184933 32
1787184938 32
1787184943 32
1787184948 32
1787184953 32
1787184958 32
1787184963 32
1787184968 36
1787184973 36
1787184978 40
1787184983 40
1787184988 40
1787184993 40
```
</details>

---

