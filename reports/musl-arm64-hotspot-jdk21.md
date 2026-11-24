---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 05:51:09 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 14 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1795517161 40
1795517166 40
1795517171 35
1795517176 35
1795517181 35
1795517186 35
1795517191 35
1795517196 35
1795517201 35
1795517206 35
1795517211 33
1795517216 33
1795517221 33
1795517226 33
1795517231 33
1795517236 33
1795517241 33
1795517246 33
1795517251 33
1795517256 33
```
</details>

---

