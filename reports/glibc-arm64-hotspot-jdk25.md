---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 05:42:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 9 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793875122 49
1793875127 49
1793875132 49
1793875137 49
1793875142 49
1793875147 49
1793875152 49
1793875157 49
1793875162 49
1793875167 49
1793875172 49
1793875177 51
1793875182 51
1793875187 51
1793875192 51
1793875197 51
1793875202 51
1793875207 51
1793875212 51
1793875217 51
```
</details>

---

