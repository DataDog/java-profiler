---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:21:27 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (3 unique values: 43-64 cores)</summary>

```
1795706155 43
1795706160 43
1795706165 43
1795706170 48
1795706175 48
1795706180 48
1795706185 48
1795706190 48
1795706195 48
1795706200 48
1795706205 48
1795706210 48
1795706215 48
1795706220 48
1795706225 48
1795706230 48
1795706235 48
1795706240 64
1795706245 64
1795706250 64
```
</details>

---

