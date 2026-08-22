---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 11:45:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1787413231 48
1787413236 48
1787413241 46
1787413246 46
1787413251 46
1787413256 46
1787413261 46
1787413266 46
1787413271 41
1787413276 41
1787413281 43
1787413286 43
1787413291 43
1787413296 43
1787413301 43
1787413306 43
1787413311 43
1787413316 43
1787413321 43
1787413326 43
```
</details>

---

