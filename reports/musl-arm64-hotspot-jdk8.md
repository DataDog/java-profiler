---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-22 11:45:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1787413232 48
1787413237 48
1787413242 46
1787413247 46
1787413252 46
1787413257 46
1787413262 46
1787413267 46
1787413272 41
1787413277 41
1787413282 43
1787413287 43
1787413292 43
1787413297 43
1787413302 43
1787413307 43
1787413312 43
1787413317 43
1787413322 43
1787413327 43
```
</details>

---

