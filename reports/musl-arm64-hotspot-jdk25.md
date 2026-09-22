---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:28:36 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 14 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790094076 48
1790094081 48
1790094087 48
1790094092 48
1790094097 48
1790094102 48
1790094107 48
1790094112 48
1790094117 48
1790094122 48
1790094127 48
1790094132 48
1790094137 48
1790094142 48
1790094147 48
1790094152 48
1790094157 48
1790094162 48
1790094167 48
1790094172 48
```
</details>

---

