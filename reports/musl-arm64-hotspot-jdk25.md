---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 02:32:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 8 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789712707 32
1789712712 32
1789712717 32
1789712722 32
1789712727 32
1789712732 32
1789712737 32
1789712742 32
1789712747 32
1789712752 32
1789712757 32
1789712762 32
1789712767 32
1789712772 32
1789712777 32
1789712782 32
1789712787 32
1789712792 32
1789712797 32
1789712802 32
```
</details>

---

