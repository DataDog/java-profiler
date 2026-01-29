---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-29 06:14:26 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 58-63 cores)</summary>

```
1769684935 58
1769684940 58
1769684945 58
1769684950 58
1769684955 58
1769684960 58
1769684965 58
1769684970 58
1769684975 58
1769684980 58
1769684985 58
1769684990 58
1769684995 58
1769685000 58
1769685005 58
1769685010 58
1769685015 58
1769685020 58
1769685025 58
1769685030 63
```
</details>

---

