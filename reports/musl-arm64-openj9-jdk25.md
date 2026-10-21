---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 11:27:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (1 unique values: 12-12 cores)</summary>

```
1792596167 12
1792596172 12
1792596177 12
1792596182 12
1792596187 12
1792596192 12
1792596197 12
1792596202 12
1792596207 12
1792596212 12
1792596217 12
1792596222 12
1792596227 12
1792596232 12
1792596237 12
1792596242 12
1792596247 12
1792596252 12
1792596257 12
1792596262 12
```
</details>

---

