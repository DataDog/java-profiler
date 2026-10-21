---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 05:55:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792576217 30
1792576222 30
1792576227 30
1792576232 30
1792576237 30
1792576242 30
1792576247 30
1792576252 30
1792576257 30
1792576262 30
1792576267 30
1792576272 30
1792576277 30
1792576282 30
1792576287 30
1792576292 30
1792576297 32
1792576302 32
1792576307 32
1792576312 32
```
</details>

---

