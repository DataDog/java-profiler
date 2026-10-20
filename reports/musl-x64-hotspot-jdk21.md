---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 10:11:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (5 unique values: 84-92 cores)</summary>

```
1792505007 92
1792505012 92
1792505017 92
1792505022 92
1792505027 92
1792505032 92
1792505037 87
1792505042 87
1792505047 87
1792505052 87
1792505057 87
1792505062 87
1792505067 87
1792505072 84
1792505077 84
1792505082 84
1792505087 84
1792505092 84
1792505097 84
1792505102 86
```
</details>

---

