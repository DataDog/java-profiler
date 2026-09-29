---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 09:12:06 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790687085 38
1790687090 38
1790687095 38
1790687100 38
1790687105 38
1790687111 38
1790687116 38
1790687121 38
1790687126 43
1790687131 43
1790687136 43
1790687141 43
1790687146 43
1790687151 43
1790687156 43
1790687161 43
1790687166 43
1790687171 43
1790687176 43
1790687181 43
```
</details>

---

