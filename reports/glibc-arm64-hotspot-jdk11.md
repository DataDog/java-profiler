---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 10:10:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1792505027 39
1792505032 39
1792505037 34
1792505042 34
1792505047 34
1792505052 34
1792505057 34
1792505062 34
1792505067 34
1792505072 34
1792505077 34
1792505082 34
1792505087 34
1792505092 34
1792505097 34
1792505102 34
1792505107 34
1792505112 34
1792505117 34
1792505122 34
```
</details>

---

