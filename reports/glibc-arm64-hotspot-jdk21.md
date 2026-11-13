---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:36:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 13 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1794594738 47
1794594743 47
1794594748 42
1794594753 42
1794594758 42
1794594763 42
1794594768 42
1794594773 42
1794594778 42
1794594783 42
1794594788 42
1794594793 42
1794594798 42
1794594803 42
1794594808 42
1794594813 42
1794594818 47
1794594823 47
1794594828 47
1794594833 47
```
</details>

---

