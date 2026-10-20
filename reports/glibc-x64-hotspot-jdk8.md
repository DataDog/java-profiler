---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-20 10:11:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 22-56 cores)</summary>

```
1792505017 30
1792505022 30
1792505027 22
1792505032 22
1792505037 22
1792505042 22
1792505047 56
1792505052 56
1792505057 56
1792505062 56
1792505067 56
1792505072 56
1792505077 56
1792505082 56
1792505087 56
1792505092 56
1792505097 56
1792505102 56
1792505107 56
1792505112 56
```
</details>

---

