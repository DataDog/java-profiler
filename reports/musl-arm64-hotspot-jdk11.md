---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 07:13:57 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 14 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790680145 38
1790680150 43
1790680155 43
1790680160 43
1790680165 43
1790680170 43
1790680175 43
1790680180 43
1790680185 43
1790680190 43
1790680195 43
1790680200 43
1790680205 43
1790680210 43
1790680215 43
1790680220 43
1790680225 43
1790680230 43
1790680235 43
1790680240 43
```
</details>

---

