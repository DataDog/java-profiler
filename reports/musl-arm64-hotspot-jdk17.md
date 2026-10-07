---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 01:04:09 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1791349084 52
1791349089 52
1791349094 52
1791349099 52
1791349104 52
1791349109 52
1791349114 52
1791349119 50
1791349124 50
1791349129 50
1791349134 50
1791349139 50
1791349144 50
1791349149 50
1791349154 50
1791349159 50
1791349164 50
1791349169 52
1791349174 52
1791349179 52
```
</details>

---

