---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 16:31:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 90-92 cores)</summary>

```
1793305676 91
1793305681 91
1793305686 91
1793305691 92
1793305696 92
1793305701 92
1793305706 92
1793305711 92
1793305716 92
1793305721 92
1793305726 92
1793305731 92
1793305736 92
1793305741 92
1793305746 92
1793305751 92
1793305756 92
1793305761 92
1793305766 92
1793305771 92
```
</details>

---

