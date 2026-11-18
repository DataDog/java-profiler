---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 14:50:20 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1795031142 48
1795031147 43
1795031152 43
1795031157 43
1795031162 43
1795031167 43
1795031172 43
1795031177 43
1795031182 43
1795031187 38
1795031192 38
1795031197 38
1795031202 38
1795031207 38
1795031212 43
1795031217 43
1795031222 38
1795031227 38
1795031232 38
1795031237 38
```
</details>

---

