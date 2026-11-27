---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 08:26:50 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 42-64 cores)</summary>

```
1795785667 42
1795785672 42
1795785677 42
1795785682 42
1795785687 42
1795785692 42
1795785697 42
1795785702 42
1795785707 42
1795785712 64
1795785717 64
1795785722 64
1795785727 64
1795785732 64
1795785737 47
1795785742 47
1795785747 47
1795785752 47
1795785757 47
1795785762 47
```
</details>

---

