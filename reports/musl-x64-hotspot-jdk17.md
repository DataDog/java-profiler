---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-13 03:49:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1786607118 45
1786607123 45
1786607128 45
1786607133 45
1786607138 45
1786607143 45
1786607148 43
1786607153 43
1786607158 43
1786607163 43
1786607168 43
1786607173 43
1786607178 43
1786607183 43
1786607188 43
1786607193 43
1786607198 43
1786607203 43
1786607208 43
1786607213 43
```
</details>

---

