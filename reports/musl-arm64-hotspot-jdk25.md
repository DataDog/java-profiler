---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:43:59 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793101154 51
1793101159 51
1793101164 51
1793101169 51
1793101174 51
1793101179 51
1793101184 51
1793101189 51
1793101194 51
1793101199 51
1793101204 51
1793101209 51
1793101214 51
1793101219 51
1793101224 51
1793101229 51
1793101234 51
1793101239 51
1793101244 51
1793101249 46
```
</details>

---

