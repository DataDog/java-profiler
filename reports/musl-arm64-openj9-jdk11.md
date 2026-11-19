---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:14:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1004 |
| Sample Rate | 16.73/sec |
| Health Score | 1046% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 15-20 cores)</summary>

```
1795097212 15
1795097217 15
1795097222 15
1795097227 15
1795097232 15
1795097237 20
1795097242 20
1795097247 20
1795097252 20
1795097257 20
1795097262 20
1795097267 20
1795097272 20
1795097277 20
1795097282 20
1795097287 20
1795097292 20
1795097297 20
1795097302 20
1795097307 20
```
</details>

---

