---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 10:47:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 14 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791384056 48
1791384061 48
1791384066 48
1791384071 48
1791384076 48
1791384081 48
1791384086 48
1791384091 48
1791384096 48
1791384101 48
1791384106 48
1791384111 48
1791384116 48
1791384121 48
1791384126 43
1791384131 43
1791384136 43
1791384141 43
1791384146 43
1791384151 43
```
</details>

---

